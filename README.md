# QtMapKit

Google Map API for Qt (C++).


## Why QtMapKit?

Qt, unlike many other modern GUI frameworks, lacks map support. With the brilliant [Qt WebKit Bridge](http://qt-project.org/doc/qt-4.8/qtwebkit-bridge.html), we have access to the probably most advanced Map in the world via its JavScript API, but I still find myself repeating myself way too many times copying JavaScript and HTML files from project to project just to have a simple map.

That's why I start this project. QtMapKit intends to be a works-out-of-the-box library that wraps everyday uses of the Google Map JavaScript API into a QWidget, bridging accessors and events to make it easier for Qt code interact with the JavaScript map. Some data classes are also made to represent geographic information, as an attempt to make the integration more seamless.

## How to Get Started

* Download the source code
* Run `qmake` and then `make`. This builds both the library and the demo.
* `make install` to install the library into `/usr/lib`.

Note: Currently the installation only works on Unix-like OSs. You need to manually modify `src.pro` to make it work with Windows.

Documentation is currently lacking, as my current aim is to complete most of the API first. You can take a look at the demo project to see how the map works. Most of the signals and acessors are merely wrappers to the [Google Map JavaScript API v3](https://developers.google.com/maps/documentation/javascript/), so you should be able to get some idea of how things work by comparing `QMMapView.h` to Google's documentation if you are familiar with it already.


## Dependency

* Qt 4 or greater with WebKit support.
* Internet connection.


### Notes: Satellite View

You need to have a JPEG decoder if you want to use the satellite view, so that satellite images can be decoded. This means that you need to include the `qjpeg` plugin from the `plugins/imageformats` directory, either by compiling them statically, or bundle them with your executable when you deploy. Refer to the [official documentation](http://qt-project.org/doc/qt-5/deployment-plugins.html) to find out how plugins work.

Thanks to [@crayfellow](https://github.com/crayfellow) for [reporting](https://github.com/uranusjr/QtMapKit/issues/1) this.


## License

BSD 3-clause. See contents of `LICENSE`.