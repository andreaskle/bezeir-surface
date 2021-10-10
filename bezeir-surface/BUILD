load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "bezeir-surface",
    srcs = glob([
        "*.cpp",
        "*.h",
    ]),
    data = glob(["shaders/*.glsl"]),
    defines = [
        "GLM_FORCE_RADIANS",
    ],
    deps = [
        "//opengl:utils",
        "//third_party/glad",
        "@glfw//:lib",
        "@glm//:lib",
        "@stb//:lib",
    ],
)
