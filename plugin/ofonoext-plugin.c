/*
 * Loader for the oFono extension library.
 *
 * libofonoext.so holds the slot manager, watch, cell-info and sim-info
 * implementations. This plugin exists only to start and stop them: oFono
 * dlopen()s plugins with RTLD_NOW rather than RTLD_GLOBAL, so one plugin
 * cannot resolve symbols from another. Both this plugin and the binder
 * driver link the shared library instead, and the dynamic linker resolves
 * it once.
 */
#ifndef OFONO_API_SUBJECT_TO_CHANGE
#define OFONO_API_SUBJECT_TO_CHANGE
#endif
#include <ofono/plugin.h>
#include <ofono/log.h>

extern void __ofono_slot_manager_init(void);
extern void __ofono_slot_manager_cleanup(void);

static int ofonoext_init(void)
{
	DBG("starting oFono extensions");
	__ofono_slot_manager_init();
	return 0;
}

static void ofonoext_exit(void)
{
	DBG("stopping oFono extensions");
	__ofono_slot_manager_cleanup();
}

/*
 * Lowest priority, so that this plugin's exit runs last. oFono calls the
 * plugins' exit functions in the same order as their init functions,
 * highest priority first. Drivers such as the binder plugin still walk and
 * unregister their slot driver in their own exit, which must come before
 * __ofono_slot_manager_cleanup() frees that registration. The slot manager
 * is created by whichever comes first, a driver registering or the init
 * below, so starting late is fine.
 */
OFONO_PLUGIN_DEFINE(ofonoext, "oFono extension APIs", VERSION,
			OFONO_PLUGIN_PRIORITY_LOW,
			ofonoext_init, ofonoext_exit)
