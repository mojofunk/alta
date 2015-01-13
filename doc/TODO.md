# General

Add license headers to files where necessary, using scripts to add copyright
headers and update year etc

# Build System

automatic formatting of python code

make each sub wscript standalone

# Libgleam

make dispatcher and interface and have ManualDispatcher and AutomaticDispatcher

# libmojo

## New Signals System

Object
 - SignalConnection connect_signal (signal_id, Handler, Callback)
 - void disconnect_signal (signal_id, Callback)

Callback class
 - signal id
 - Handler ref
 - message_functor
 - user_data
 
Handler class
 - call_sync (Callback, Message)
 - call_async (Callback, Message)

Closure class? Callback + Message

Signal class list of Callbacks

SignalConnection class
 - scoped signal connection

## Misc

transport should be in Engine not Application

Prevent headers being included directly?
must only include mojo.hpp and enforce it?

Use Glib::Module and remove mojo/utils/library?

Move Object class to interfaces?

Add ardour/jack_utils code to JackAudioDriverModule to get devices

Merge Worker/ApplicationWorker with gleam::dispatcher?

Rename ApplicationWorker FunctorDispatcher and inherit from gleam::ManualDispatcher

Worker should have its own thread like gleam::dispatcher

include facility for startup messages during initialization?

SearchPath should be renamed search_path so it doesn't clash with SearchPath
typedef in windows.h

SearchPath should be exposed in mojo public API so it can be used outside of
libmojo. Not worth putting it in a separate lib.

## Modules

Make a generic module infrastructure for libmojo, modules may include

AudioFile modules:
	SndfileAudioFileModule
	MadAudioFileModule
	CoreaudioAudioFileModule

MidiFile modules:
	JackMidiModule
	
AudioEffectModule:
	LADSPAEffectModule
	LV2EffectModule
	VSTEffectModule
	DXEffectModule

InstrumentModule:
	VSTInstrumentModule
	DXInstrumentModule

AudioDriverModule:
	JACKAudioDriverModule
	ALSAAudioDriverModule
	PulseAudioDriverModule
	PortAudioDriverModule
	VSTAudioDriverModule

AudioResamplerModule:
	SRCResamplerModule
	SpeexResamplerModule

ProjectImportModule
	ArdourImportModule
	AAFImportModule

ProjectExportModule
	ArdourExportModule
	AAFExportModule

Try having only one instance of a Module class per module, change
the module function to mojo_module_init () that allocates Module
class(if init hasn't already been called) and returns a pointer to
it, also add a mojo_module_fini () function to deallocate any
resources allocated by init for proper shutdown.

libmojo must expose a way to discover new modules

modules should only have to link to a small core library if at all

Should all platform dependent code be in a base library
which modules can link to? possibly in libgleam

## Tests

Tests should try to provide full coverage of API

All tests should also test that undo/redo work properly. one way to do
that would be to make a copy of an object then change it, check for inequality
then call undo and check for equality. also copy the changed state(before undo)
, call redo and check for equality

Create a complex new project using all data types, save, close and restore.

char encoding tests etc

Event

- split events in a Sequence
- nudge forward events
- nudge backward events

Sequence

# SMPTE

Use libltc

smpte::time interface with implementations for each time type
vs
one class with enum for each type(4)

The later may be slightly slower due to branching.

conversion to/from ltc/vitc/mtc.

# RT Graph

The graph must be directed and acyclic

graph processing must be able to support rt safe processing

There must be able to be more than one graph per process

A graph contains a number of nodes

The graph cannot have parallel edges between nodes?

Can a graph contain isolated nodes(no edges)?

A source node is a node with no incoming edges

A sink node is a node with no outgoing edges

A processing node is a node with incoming and outgoing edges

Must be able to add and remove edges.

The source nodes in the graph are processed first as they are
the source of the data and the edges are followed to process the
rest of the nodes.

The graph must be able to be processed in parallel.

Would breadth first processing be more cache friendly?

The API must expose a way to set how many threads are used to process
the graph.

get_max_thread_count

get_thread_count
set_thread_count

// optional
get_optimal_thread_count

The test suite must be able to measure total process time

The test suite must be able to measure thread context switching time.

The test suite must be able to test the effect cache size has on processing
performance.

Application API should use method names like transport_* track_* project_* etc

Application API should have a sync method for testing(at least)

Should the mojo public API be in C?

If the ApplicationWorker is calling a sync function and the UI thread is waiting for the
ApplicationWorker to finish then there is a deadlock?

If when the last project is removed can App::quit be called in an idle callback.

## Debug Macros

Need simple debug library for logging messages.
	- only compiled in debug mode?
	- M_DEBUG_ASSERT
	- M_DEBUG_LOG just takes a string
	- records line and file
	- filters?
	- optional namespace?
	- command line args?
	- header only?
	- per thread logging streams?

waf test target

timer library for measuring execution time
	- interface with backends
	- macro for debug compiling
	- records line and file
	- per thread timers?
	- BEGIN and END or RAII?

# User Interface

ui::Application inherits from Gtk::Application or stick to composition?

Track Canvas
	- change height from the track view list
	- add border/frame to TrackViewListItem

Add ToolButtons class

Rename TransportToolbar TransportButtons

Add Stop, Locate to start, Locate to End buttons to TransportButtons

Add Inspector class
Add StatusLine class
Add InfoLine class
Add ProjectOverview class

Add WindowLayoutDialog and button to ProjectWindowToolbar

# Docs

Dev guide section on including headers using " instead of <

Dev guide section on why _t shouldn't be used for typedefs but
why we do anyway

Convert docs to publician

Update section on header include guards include style where there
is no class defined in the file. eg mojo/core/typedefs.hpp ->
MOJO_CORE_TYPEDEFS

Add section on typedefs for Glib::RefPtr and boost::shared_ptr

Section on mojo/macros.hpp forward class decl and typedefs.

Section on file name standard for test files

Add README
