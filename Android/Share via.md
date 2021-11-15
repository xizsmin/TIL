- 유저가 Intent.ACTION_SEND handle 가능한 앱을 chooser에서 선택할 수 있게 유도

```kotlin

// Creating our Share Intent
private fun getShareIntent() : Intent {

   val args = GameWonFragmentArgs.fromBundle(requireArguments())
   val shareIntent = Intent(Intent.ACTION_SEND)
   
   shareIntent.setType("text/plain")
            .putExtra(Intent.EXTRA_TEXT, getString(R.string.share_text, args.arg1, args.arg2))
   return shareIntent
   
}

// Starting an Activity with our new Intent
private fun shareSuccess() {

   startActivity(getShareIntent())
   
}

// Check if there exists an app which can handle the intent
{
  // ...
  
  if(getShareIntent().resolveActivity(requireActivity().packageManager)==null) {
  
      // Hiding ui components for sharing service, etc...
      
  }
  
  //...
}

```

