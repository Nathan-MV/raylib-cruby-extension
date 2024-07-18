# Ruby C Extension for Raylib

## Instalation

If possible, try the artifacts from the CI instead of compiling. Please give me a heads up if they don't work out of the box: [CI Artifacts](https://github.com/Nathan-MV/raylib-cruby-extension/actions)

## Compilation

- Clone Repository
```
git clone https://github.com/Nathan-MV/raylib-cruby-extension
```

- Init Submodules
```
cd raylib-cruby-extension
git submodule update --init --recursive
```

- Install Dependencies
```
bundle install --with compile
```

- Raylib Dependencies (Ubuntu)
```
sudo apt install cmake ninja-build ruby-devel libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

- Raylib Dependencies (Fedora)
```
sudo dnf install cmake ninja-build ruby-devel alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic wayland-devel libxkbcommon-devel wayland-protocols-devel
```

- Raylib Dependencies (Arch Linux)
```
sudo pacman -S cmake ninja ruby alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
```

- Compile (Ruby Extension)
```
rake
```

- Compile (Binary)
Note: Require CMake, Ninja and Ruby 3.3 (Currently the Windows binary does not work, help is appreciated)
```
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE:STRING=Release
cmake --build build --config Release --target all
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/Nathan-MV/raylib-cruby-extension. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/Nathan-MV/raylib-cruby-extension/blob/master/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the HelloC project's codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/Nathan-MV/raylib-cruby-extension/blob/master/CODE_OF_CONDUCT.md).
