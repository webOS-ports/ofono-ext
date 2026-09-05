# ofono-ext

oFono extension APIs: the slot manager, modem watch, cell-info and sim-info
APIs that Sailfish OS carries inside its oFono fork, built out of tree against
upstream oFono. ofono-binder-plugin links this rather than requiring a forked
daemon.

The sources are the Sailfish extension layer, taken verbatim from
[sailfishos/ofono](https://github.com/sailfishos/ofono) at revision
`bea32ca9a931e77cb6d37800c06fead44265507f` and reworked only in their
`#include` lines. See `src/ofono-ext-compat.h` for every assumption this
package makes about oFono's internals.

The extension APIs live in a shared library (`libofonoext`) that both the
loader plugin and ofono-binder-plugin link, because ofonod dlopen()s plugins
with `RTLD_NOW`, not `RTLD_GLOBAL`, so one plugin cannot resolve symbols from
another. Undefined `__ofono_*` symbols are expected: they are resolved from
ofonod at load time, so the library is only meaningful alongside a matching
oFono.

## License

GPL-2.0-only, as inherited from the Sailfish oFono sources.
