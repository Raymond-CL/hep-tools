# How to Rust

1. Create a new rust project with cargo.

   ```bash
   cargo new <prject_name> --vcs none
   ```

   The `--vcs` version control flag is set to none so it won't create link to `Git`.

2. Make sure to open `<project_name>` folder with VScode is you want `rust_analyzer` to work.
3. Code in `<project_name>/src/main.rs`.
4. Build by running `cargo build` in `<project_name>/` directory.
5. Execute binary in `<project_name>/target/debug/<project_name>`.
