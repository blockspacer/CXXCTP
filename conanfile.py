from conans import ConanFile, CMake, tools
import traceback
import os
import shutil

# Just replace `MySimpleProject` with your name
class MySimpleProject(ConanFile):
    name = "CXXCTP"

    # Indicates License type of the packaged library
    license = "MIT"

    version = "master"
    url = "https://github.com/blockspacer/CXXCTP"
    description = "C++ compile-time programming (serialization, reflection, code modification, enum to string, better enum, enum to json, extend or parse language, etc.)."

    # Packages the license for the conanfile.py
    exports = ["LICENSE.md"]

    settings = "os", "compiler", "build_type", "arch"

    # Use version ranges for dependencies unless there's a reason not to
    requires = (
#        "fmt/[>=4.1.0]@bincrafters/stable",
#        "spdlog/[>=0.14.0]@bincrafters/stable",
        "FakeIt/[>=2.0.4]@gasuketsu/stable",
        "catch2/[>=2.1.0]@bincrafters/stable"
    )

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
    generators = "cmake"
    default_options = \
        "boost:without_atomic=True", \
        "boost:without_chrono=True", \
        "boost:without_container=True", \
        "boost:without_context=True", \
        "boost:without_coroutine=True", \
        "boost:without_graph=True", \
        "boost:without_graph_parallel=True", \
        "boost:without_log=True", \
        "boost:without_math=True", \
        "boost:without_mpi=True", \
        "boost:without_serialization=True", \
        "boost:without_signals=True", \
        "boost:without_test=True", \
        "boost:without_timer=True", \
        "boost:without_type_erasure=True", \
        "boost:without_wave=True", \
        "FakeIt:integration=catch", \
        "*:shared=False"

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
#
#    def imports(self):
#        dest = os.getenv("CONAN_IMPORT_PATH", "bin")
#        self.copy("*.dll", dst=dest, src="bin")
#        self.copy("*.dylib*", dst=dest, src="lib")
#        self.copy("cacert.pem", dst=dest, src=".")