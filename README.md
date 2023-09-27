# Simple bash script to install SuperLU

This script fetches [SuperLU](https://github.com/xiaoyeli/superlu), compiles the code, and install the resulting files to `/usr/local`.

**Note:** The installation directories are `/usr/local/include/superlu` and `/usr/local/lib/superlu`.

```bash
bash install-deps.bash
bash install-superlu.bash
```

## Installed include files

Output of `tree /usr/local/include/superlu`

```text
/usr/local/include/superlu
├── colamd.h
├── slu_cdefs.h
├── slu_Cnames.h
├── slu_dcomplex.h
├── slu_ddefs.h
├── slu_scomplex.h
├── slu_sdefs.h
├── slu_util.h
├── slu_zdefs.h
├── superlu_config.h
├── superlu_enum_consts.h
└── supermatrix.h

1 directory, 12 files
```

## Installed lib files

Output of `tree /usr/local/lib/superlu`

```text
/usr/local/lib/superlu
├── libsuperlu.so -> libsuperlu.so.6
├── libsuperlu.so.6 -> libsuperlu.so.6.0.1
└── libsuperlu.so.6.0.1

1 directory, 3 files
```
