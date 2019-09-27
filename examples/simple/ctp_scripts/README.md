# About
Utils must load before scripts (`Cling` related), so we added `1_`, `2_`, ... before folder names.

 NOTE
scripts placed here will be executed at runtime with `CXXCTP_tool` and `Cling`, you may want to make them built-in C++ plugins because of performance reasons.

# NOTE
Make sure file names are globally unique.
