// Query the current state of a lifecycle and do something accordingly

...
if (lifecycle.currentState.isAtLeast(Lifecycle.State.STARTED)) {
	// do something 
}

// adding an observer
class MyObserver : DefaultLifecycleObserver {
    override fun onResume(owner: LifecycleOwner) {
        connect()
    }

    override fun onPause(owner: LifecycleOwner) {
        disconnect()
    }
}

lifecycleOwner.getLifecycle().addObserver(this)

