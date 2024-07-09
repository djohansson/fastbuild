vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO djohansson/fastbuild
    REF 381bf79990f6acd9bfcd62333158b5fae3e8a9bd
    SHA512 b5ffff369f82dc899e9ffa44bd2a0b2247722bc67d305b30963e7a24939d93efb7e83f30bf7a046e70c1402d902b0e057b7ceaa8d0dd0b38afdeba17aa4855d4
    HEAD_REF master
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME "fastbuild")

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(INSTALL "${SOURCE_PATH}/Code/LICENSE.txt" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
