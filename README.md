# Ruby C Extension for Raylib

## Installation

1. Clone Repository
```
git clone https://github.com/Nathan-MV/raylib-cruby-extension --recursive
```

2. Install Dependencies
```
bundle install
```

3. Compile it
```
rake
```

## Cheatsheet

### Color Class Methods

| Method                                   | Status     |
|------------------------------------------|------------|
| [fade(alpha)](ext/rubyraylib/color.c#rb_color_fade) | ✔️ |
| [to_int](ext/rubyraylib/color.c#rb_color_to_int) | ✔️ |
| [normalize](ext/rubyraylib/color.c#rb_color_normalize) | ✔️ |
| [to_hsv](ext/rubyraylib/color.c#rb_color_to_hsv) | ✔️ |
| [tint(tint)](ext/rubyraylib/color.c#rb_color_tint) | ✔️ |
| [brightness(factor)](ext/rubyraylib/color.c#rb_color_brightness) | ✔️ |
| [contrast(contrast)](ext/rubyraylib/color.c#rb_color_contrast) | ✔️ |
| [alpha_blend(src, tint)](ext/rubyraylib/color.c#rb_color_alpha_blend) | ✔️ |
| pixel_color(format) | ❌ |
| pixel_color=(dst, format)  | ❌ |
| pixel_data_size(width, height, format) | ❌ |


## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/Nathan-MV/raylib-cruby-extension. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/Nathan-MV/raylib-cruby-extension/blob/master/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the HelloC project's codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/Nathan-MV/raylib-cruby-extension/blob/master/CODE_OF_CONDUCT.md).
