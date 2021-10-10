# Based on:
# https://github.com/pbellis/bazel-glfw

# MIT License
#
# Copyright (c) 2019 pbellis
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

WIN32_DEFINES = [
    "_GLFW_WIN32",
]

WIN32_HDRS = [
    "src/win32_joystick.h",
    "src/win32_platform.h",
    "src/wgl_context.h", 
]

WIN32_SRCS = [
    "src/win32_init.c",
    "src/win32_joystick.c",
    "src/win32_monitor.c",
    "src/win32_thread.c",
    "src/win32_time.c",
    "src/win32_window.c",
    "src/wgl_context.c",
]

WIN32_LINKOPTS = [
    "-DEFAULTLIB:user32.lib",
    "-DEFAULTLIB:gdi32.lib",
    "-DEFAULTLIB:shell32.lib",
]

LINUX_DEFINES = [
    "_GLFW_HAS_XF86VM",
    "_GLFW_X11",
]

LINUX_HDRS = [
    "src/glx_context.h",
    "src/linux_joystick.h",
    "src/posix_thread.h",
    "src/posix_time.h",
    "src/x11_platform.h",
]

LINUX_SRCS = [
    "src/glx_context.c",
    "src/linux_joystick.c",
    "src/posix_thread.c",
    "src/posix_time.c",
    "src/x11_init.c",
    "src/x11_monitor.c",
    "src/x11_window.c",
]

LINUX_LINKOPTS = ["-ldl", "-lX11", "-lpthread"]

cc_library(
    name = "glfw_src",
    hdrs = [
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        "src/egl_context.h",
        "src/internal.h",
        "src/osmesa_context.h",
        "src/mappings.h",
        "src/xkb_unicode.h",
    ] + select({
		"@bazel_tools//src/conditions:windows": WIN32_HDRS,
		"@bazel_tools//src/conditions:linux_x86_64": LINUX_HDRS,
	}),
    srcs = [
        "src/context.c",
        "src/egl_context.c",
        "src/init.c",
        "src/input.c",
        "src/osmesa_context.c",
        "src/monitor.c",
        "src/vulkan.c",
        "src/window.c",
        "src/xkb_unicode.c",
    ] + select({
		"@bazel_tools//src/conditions:windows": WIN32_SRCS,
		"@bazel_tools//src/conditions:linux_x86_64": LINUX_SRCS,
	}),
    defines = select({
		"@bazel_tools//src/conditions:windows": WIN32_DEFINES,
		"@bazel_tools//src/conditions:linux_x86_64": LINUX_DEFINES,
	}),
)

cc_library(
    name = "lib",
    hdrs = [
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
    ],
    linkopts = select({
		"@bazel_tools//src/conditions:windows": WIN32_LINKOPTS,
		"@bazel_tools//src/conditions:linux_x86_64": LINUX_LINKOPTS,
	}),
    deps = [":glfw_src"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)