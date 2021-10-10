load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

new_git_repository(
    name = "glm",
    build_file = "@//third_party:glm.BUILD",
    remote = "https://github.com/g-truc/glm.git",
    tag = "0.9.9.7",
)

new_git_repository(
    name = "stb",
    branch = "master",
    build_file = "@//third_party:stb.BUILD",
    remote = "https://github.com/nothings/stb.git",
)

http_archive(
    name = "catch2",
    strip_prefix = "Catch2-2.13.0",
    urls = ["https://github.com/catchorg/Catch2/archive/v2.13.0.tar.gz"],
)

new_git_repository(
    name = "glfw",
    build_file = "@//third_party:glfw.BUILD",
    remote = "https://github.com/glfw/glfw.git",
    tag = "3.3.2",
)
