#include <table_bindings.h>

VALUE rb_cTable;

class Table {
public:
  int xsize, ysize, zsize, dim;
  std::vector<uint16_t> data;
  int z_multiplier;

  Table(int x, int y = 0, int z = 0) {
    if (x <= 0 || y < 0 || z < 0) {
      rb_raise(rb_eArgError, "x must be positive, y and z non-negative integers");
    }

    dim = 1 + (y > 0 ? 1 : 0) + (z > 0 ? 1 : 0);
    xsize = x;
    ysize = (y > 0) ? y : 1;
    zsize = (z > 0) ? z : 1;
    update_z_multiplier();
    data.resize(xsize * ysize * zsize);
  }

  inline uint16_t get(int x, int y = 0, int z = 0) const noexcept {
    return data[x + y * xsize + z * z_multiplier];
  }

  inline void set(int x, int y, int z, uint16_t value) noexcept {
    data[x + y * xsize + z * z_multiplier] = value;
  }

  void resize(int nx, int ny = 0, int nz = 0) {
    ny = (ny > 0) ? ny : 1;
    nz = (nz > 0) ? nz : 1;
    if (nx == xsize && ny == ysize && nz == zsize) return;

    std::vector<uint16_t> new_data(nx * ny * nz);
    int min_x = std::min(xsize, nx);
    int min_y = std::min(ysize, ny);
    int min_z = std::min(zsize, nz);

    for (int x = 0; x < min_x; ++x) {
      for (int y = 0; y < min_y; ++y) {
        for (int z = 0; z < min_z; ++z) {
          new_data[x + y * nx + z * nx * ny] = data[x + y * xsize + z * z_multiplier];
        }
      }
    }

    xsize = nx;
    ysize = ny;
    zsize = nz;
    data = std::move(new_data);
    update_z_multiplier();
  }

  VALUE dump() const {
    VALUE str = rb_str_new(nullptr, 20 + data.size() * sizeof(uint16_t));
    uint32_t* metadata = (uint32_t*)RSTRING_PTR(str);
    metadata[0] = dim;
    metadata[1] = xsize;
    metadata[2] = ysize;
    metadata[3] = zsize;
    metadata[4] = data.size();
    uint16_t* content = (uint16_t*)(metadata + 5);
    std::copy(data.begin(), data.end(), content);
    return str;
  }

  static Table* load(VALUE s) {
    uint32_t* metadata = (uint32_t*)RSTRING_PTR(s);
    int size = metadata[4];
    if (size == 0 || metadata[1] == 0) return nullptr;

    Table* table = new Table(metadata[1], metadata[2], metadata[3]);
    table->data.resize(size);
    uint16_t* content = (uint16_t*)(metadata + 5);
    std::copy(content, content + size, table->data.begin());
    return table;
  }

private:
  void update_z_multiplier() { z_multiplier = xsize * ysize; }
};

static VALUE rb_table_allocate(VALUE self) {
  Table* table = new Table(1, 1, 1);
  return Data_Wrap_Struct(self, NULL, rb_object_free<Table>, table);
}

inline Table* get_table(VALUE obj) {
  Table* table;
  Data_Get_Struct(obj, Table, table);
  return table;
}

static VALUE rb_table_initialize(VALUE self, VALUE x, VALUE y, VALUE z) {
  auto* table = get_table(self);

  int ix = NUM2INT(x);
  int iy = NIL_P(y) ? 0 : NUM2INT(y);
  int iz = NIL_P(z) ? 0 : NUM2INT(z);

  *table = Table(ix, iy, iz);
  return self;
}

static VALUE rb_table_xsize(VALUE self) {
  Table* table = get_table(self);
  return INT2NUM(table->xsize);
}

static VALUE rb_table_ysize(VALUE self) {
  Table* table = get_table(self);
  return INT2NUM(table->ysize);
}

static VALUE rb_table_zsize(VALUE self) {
  Table* table = get_table(self);
  return INT2NUM(table->zsize);
}

static VALUE rb_table_get(int argc, VALUE* argv, VALUE self) {
  VALUE rb_x, rb_y, rb_z;

  rb_scan_args(argc, argv, "12", &rb_x, &rb_y, &rb_z);

  auto* table = get_table(self);
  int ix = NUM2INT(rb_x);
  int iy = NIL_P(rb_y) ? 0 : NUM2INT(rb_y);
  int iz = NIL_P(rb_z) ? 0 : NUM2INT(rb_z);

  return UINT2NUM(table->get(ix, iy, iz));
}

static VALUE rb_table_set(int argc, VALUE* argv, VALUE self) {
  VALUE rb_x, rb_y, rb_z, rb_value;

  rb_scan_args(argc, argv, "22", &rb_x, &rb_y, &rb_z, &rb_value);

  auto* table = get_table(self);
  int ix = NUM2INT(rb_x);
  int iy = NIL_P(rb_y) ? 0 : NUM2INT(rb_y);
  int iz = NIL_P(rb_z) ? 0 : NUM2INT(rb_z);
  uint16_t val = NUM2UINT(rb_value);

  table->set(ix, iy, iz, val);

  return Qnil;
}

static VALUE rb_table_resize(int argc, VALUE* argv, VALUE self) {
  VALUE rb_x, rb_y, rb_z;

  rb_scan_args(argc, argv, "22", &rb_x, &rb_y, &rb_z);

  auto* table = get_table(self);
  int inx = NUM2INT(rb_x);
  int iny = NIL_P(rb_y) ? 0 : NUM2INT(rb_y);
  int inz = NIL_P(rb_z) ? 0 : NUM2INT(rb_z);

  table->resize(inx, iny, inz);

  return Qnil;
}

static VALUE rb_table_dump(VALUE self) {
  auto* table = get_table(self);
  return table->dump();
}

static VALUE rb_table_load(VALUE self, VALUE str) {
  Table* table = Table::load(str);
  return Data_Wrap_Struct(rb_cTable, NULL, rb_object_free<Table>, table);
}

// Ruby Extension Initialization
extern "C" void Init_Table() {
  rb_cTable = rb_define_class_under(rb_mRL, "Table", rb_cObject);
  rb_define_alloc_func(rb_cTable, rb_table_allocate);

  rb_define_method(rb_cTable, "initialize", rb_table_initialize, 3);
  rb_define_method(rb_cTable, "xsize", rb_table_xsize, 0);
  rb_define_method(rb_cTable, "ysize", rb_table_ysize, 0);
  rb_define_method(rb_cTable, "zsize", rb_table_zsize, 0);
  rb_define_method(rb_cTable, "[]", rb_table_get, -1);
  rb_define_method(rb_cTable, "[]=", rb_table_set, -1);
  rb_define_method(rb_cTable, "resize", rb_table_resize, -1);
  rb_define_method(rb_cTable, "_dump", rb_table_dump, 0);
  rb_define_singleton_method(rb_cTable, "_load", rb_table_load, 1);
}
