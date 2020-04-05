from conans import ConanFile, CMake, tools
import traceback
import os
import shutil

class CXXCTPProject(ConanFile):
    name = "CXXCTP"

    # Indicates License type of the packaged library
    license = "MIT"

    version = "master"
    url = "https://github.com/blockspacer/CXXCTP"
    description = "C++ compile-time programming (serialization, reflection, code modification, enum to string, better enum, enum to json, extend or parse language, etc.)."
    topics = ('c++')

    options = {
        "use_system_boost": [True, False],
        "enable_tests": [True, False],
        "enable_sanitizers": [True, False]
    }

    default_options = (
        "use_system_boost=False",
        "enable_tests=False",
        "enable_sanitizers=False",
        # boost
        "boost:without_atomic=True",
        "boost:without_chrono=True",
        "boost:without_container=True",
        "boost:without_context=True",
        "boost:without_coroutine=True",
        "boost:without_graph=True",
        "boost:without_graph_parallel=True",
        "boost:without_log=True",
        "boost:without_math=True",
        "boost:without_mpi=True",
        "boost:without_serialization=True",
        "boost:without_test=True",
        "boost:without_timer=True",
        "boost:without_type_erasure=True",
        "boost:without_wave=True",
        # FakeIt
        "FakeIt:integration=catch",
        # build
        "*:shared=False",
        "openssl:shared=True"
    )

    generators = 'cmake_find_package', "cmake", "cmake_paths"

    #default_options = \
    #    "boost:without_atomic=True", \
    #    "boost:without_chrono=True", \
    #    "boost:without_container=True", \
    #    "boost:without_context=True", \
    #    "boost:without_coroutine=True", \
    #    "boost:without_graph=True", \
    #    "boost:without_graph_parallel=True", \
    #    "boost:without_log=True", \
    #    "boost:without_math=True", \
    #    "boost:without_mpi=True", \
    #    "boost:without_serialization=True", \
    #    "boost:without_signals=True", \
    #    "boost:without_test=True", \
    #    "boost:without_timer=True", \
    #    "boost:without_type_erasure=True", \
    #    "boost:without_wave=True", \
    #    "FakeIt:integration=catch", \
    #    "*:shared=False"

    # Packages the license for the conanfile.py
    #exports = ["LICENSE.md"]
    exports_sources = ("LICENSE", "README.md", "include/*", "src/*",
                       "cmake/*", "CMakeLists.txt", "tests/*", "benchmarks/*",
                       "scripts/*")

    settings = "os", "compiler", "build_type", "arch"


    def requirements(self):
        if self.options.enable_tests:
            self.requires("catch2/[>=2.1.0]@bincrafters/stable")
            self.requires("gtest/[>=1.8.0]@bincrafters/stable")
            self.requires("FakeIt/[>=2.0.4]@gasuketsu/stable")

        if not self.options.use_system_boost:
            self.requires("boost/1.71.0@dev/stable")

        self.requires("chromium_build_util/master@conan/stable")

        self.requires("chromium_base/master@conan/stable")

        self.requires("corrade/2019.10@magnum/stable")

        self.requires("type_safe/0.2@conan/stable")

        self.requires("double-conversion/3.1.1@bincrafters/stable")

        self.requires("gflags/2.2.2@bincrafters/stable")

        self.requires("glog/0.4.0@bincrafters/stable")

        # patched to support "openssl/OpenSSL_1_1_1-stable@conan/stable"
        #self.requires("libevent/2.1.11@dev/stable")

        self.requires("lz4/1.8.3@bincrafters/stable")

        # must match openssl version used in webrtc
        ##self.requires("openssl/OpenSSL_1_1_1-stable@conan/stable")

        #self.requires("OpenSSL/1.1.1c@conan/stable")

        # patched to support "openssl/OpenSSL_1_1_1-stable@conan/stable"
        self.requires("zlib/v1.2.11@conan/stable")

        self.requires("lzma/5.2.4@bincrafters/stable")

        self.requires("zstd/1.3.8@bincrafters/stable")

        self.requires("snappy/1.1.7@bincrafters/stable")

        self.requires("bzip2/1.0.8")

        self.requires("libsodium/1.0.18@bincrafters/stable")

        self.requires("libelf/0.8.13@bincrafters/stable")

        self.requires("libdwarf/20190505@bincrafters/stable")

        self.requires("clang_folly_conan/v2019.01.14.00@conan/stable")

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def build(self):
        cmake = CMake(self)
        if self.settings.compiler == 'gcc':
            cmake.definitions["CMAKE_C_COMPILER"] = "gcc-{}".format(
                self.settings.compiler.version)
            cmake.definitions["CMAKE_CXX_COMPILER"] = "g++-{}".format(
                self.settings.compiler.version)

        cmake.definitions["ENABLE_SANITIZERS"] = 'ON'
        if not self.options.enable_sanitizers:
            cmake.definitions["ENABLE_SANITIZERS"] = 'OFF'

        cmake.definitions["ENABLE_TESTS"] = 'ON'
        if not self.options.enable_tests:
            cmake.definitions["ENABLE_TESTS"] = 'OFF'

        cmake.definitions["CMAKE_TOOLCHAIN_FILE"] = 'conan_paths.cmake'
        cmake.configure()
        cmake.build()
        cmake.test()

    # Importing files copies files from the local store to your project.
    def imports(self):
        dest = os.getenv("CONAN_IMPORT_PATH", "bin")
        self.output.info("CONAN_IMPORT_PATH is ${CONAN_IMPORT_PATH}")
        self.copy("license*", dst=dest, ignore_case=True)
        self.copy("*.dll", dst=dest, src="bin")
        self.copy("*.so", dst=dest, src="bin")
        self.copy("*.dylib*", dst=dest, src="lib")
        self.copy("*.lib*", dst=dest, src="lib")
        self.copy("*.a*", dst=dest, src="lib")

#    requires = \
#        "boost/1.68.0@conan/stable", \
#        "catch/1.5.0@TyRoXx/stable", \
#        "json/2.0.10@jjones646/stable", \
#        "msgpack/2.1.5@bincrafters/stable", \
#        "cotire/1.7.6@smspillaz/cotire", \
#        "libcurl/7.52.1@bincrafters/stable", \
#        "OpenSSL/1.0.2m@conan/stable", \
#        "sqlite3/3.21.0@bincrafters/stable", \
#        "FakeIt/master@gasuketsu/stable", \
#        "websocketpp/0.7.0@TyRoXx/stable", \
#        "zlib/1.2.11@conan/stable", \
#        "bzip2/1.0.6@conan/stable", \
#        "yaml-cpp/0.6.2@tmadden/stable", \
#        "spdlog/0.16.3@bincrafters/stable"

#       self.requires("streamvbyte/master@elshize/testing")
#        self.requires("gumbo-parser/1.0@elshize/stable")
#        self.requires("rax/master@elshize/testing")
#        self.requires("cppitertools/1.0@elshize/stable")
#        self.requires("taily/0.1@elshize/testing")
#        self.requires("ParallelSTL/20181004@elshize/stable")
#        self.requires("FakeIt/2.0.5@gasuketsu/stable")
#
#        if not self.options.use_system_boost:
#            self.requires("boost/1.66.0@conan/stable")
#        self.requires("zlib/1.2.11@conan/stable")
#        self.requires("gtest/1.8.0@conan/stable")
#        self.requires("TBB/2018_U5@conan/stable")
#
#        self.requires("range-v3/0.4.0@ericniebler/stable")
#        self.requires("CLI11/1.6.0@cliutils/stable")
#        self.requires("gsl_microsoft/1.0.0@bincrafters/stable")
#        self.requires("debug_assert/1.3@Manu343726/testing")
#        self.requires("type_safe/0.1@Manu343726/testing")
#        self.requires("gsl_microsoft/1.0.0@bincrafters/stable")
#        self.requires("jsonformoderncpp/3.1.2@vthiery/stable")
#        self.requires("spdlog/1.1.0@bincrafters/stable")

# see https://github.com/elshize/irkit/blob/master/conanfile.py
# see https://gitlab.kitware.com/ifmfr/glew/commit/25bc79f2b9f60c43cdedd91a738f087954c4228f
# see https://github.com/jgsogo/conan-spdlog_setup/blob/359e6978fbd698a13c17b46e44bdbae107fa7f3f/conanfile.py

#    def build(self):
#        cmake = CMake(self, generator='Ninja')
#        cmake.configure()
#        cmake.build()
#        cmake.test()
