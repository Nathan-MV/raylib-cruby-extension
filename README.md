# Ruby C Extension for Raylib

## Instalation

If possible try the artifacts on the CI instead of compiling and give me a heads up if it don't work out of the box
https://github.com/Nathan-MV/raylib-cruby-extension/actions

## Compilation

- Clone Repository
```
git clone https://github.com/Nathan-MV/raylib-cruby-extension --recursive
```

- Install Dependencies
```
bundle install --with compile
```

- Raylib Dependencies (Ubuntu)
```
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

- Raylib Dependencies (Fedora)
```
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic wayland-devel libxkbcommon-devel wayland-protocols-devel
```

- Raylib Dependencies (Arch Linux)
```
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
```

- Compile
```
rake
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/Nathan-MV/raylib-cruby-extension. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/Nathan-MV/raylib-cruby-extension/blob/master/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the HelloC project's codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/Nathan-MV/raylib-cruby-extension/blob/master/CODE_OF_CONDUCT.md).
