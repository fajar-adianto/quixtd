# Qt6 QML Bindings for TDLib

This project provides **Qt / QML bindings for the [TDLib Telegram library](https://github.com/tdlib/td)**, updated and modernized for **Qt6 compatibility**.  
It builds upon earlier work in:

- [qtdlib](https://github.com/dpniel/qtdlib) (original project)  
- [Teleports](https://gitlab.com/ubports/development/apps/teleports.git) (UBports modifications)

and integrates with a newer version of the [asyncfuture](https://github.com/vpicaver/asyncfuture.git) library.

---

## ✨ Key Features

- ✅ **Qt6 QML Plugin compatibility**  
- ✅ Updated to use the maintained **asyncfuture** library  
- ✅ **Translation tool cleanup** – removed dependency on `libintl.h`  
- ✅ Exposes TDLib APIs as idiomatic **Qt objects** and **QML types**  
- ✅ Designed for use in modern **Qt Quick applications**  

---

## 📦 Requirements

- [Qt 6.5+](https://www.qt.io/download) (QtQuick, QML, QtConcurrent modules)  
- [TDLib](https://github.com/tdlib/td) (compiled as shared library)  
- [asyncfuture](https://github.com/vpicaver/asyncfuture.git)  

Optional but recommended:
- CMake ≥ 3.16  
- A C++17-compatible compiler  

---

## Installation
To include QuixTd in your project, clone the repository and integrate the module into your Qt project:

```bash
git clone https://github.com/fajar-adianto/quixtd.git
```

Add the module path to your `CMakeLists.txt` file.
```cmake
add_subdirectory(quixtd)
```

Or, use `FetchContent` in your `CMakeLists.txt` file.

```cmake
FetchContent_Declare(
    quixtd
    GIT_REPOSITORY "https://github.com/fajar-adianto/quixtd.git"
    GIT_TAG main
)
FetchContent_MakeAvailable(quixtd)
```

Don't forget to add `target_link_libraries` in your `CMakeLists.txt` file.

```cmake
...
target_link_libraries(<TARGET>
    PRIVATE
        ...
        QuixTd QuixTdplugin
        ...
)
```

---

## Contributing
We welcome contributions to enhance QuixTd. To contribute:
1. Fork this repository.
2. Create a feature branch for your changes.
3. Submit a pull request with a detailed description of your improvements.

Please adhere to the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) when contributing.

---

## License
QuixTd is released under the [GNU General Public License v3](LICENSE). Feel free to use, modify, and distribute it as per the license terms.

---

## 🙏 Acknowledgments

This project would not exist without the work of the following projects:

- [TDLib Documentation](https://core.telegram.org/tdlib) – official Telegram Database Library reference.  
- [qtdlib](https://github.com/dpniel/qtdlib) – the original Qt/QML bindings for TDLib.  
- [Teleports](https://gitlab.com/ubports/development/apps/teleports.git) – UBports’ modifications and improvements.  
- [asyncfuture](https://github.com/vpicaver/asyncfuture.git) – a modern async/await library for Qt, used in this project.  
