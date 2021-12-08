
// Uri format content://item?id={id}&title={title} <- determined by the app you'd like to launch here.
val destUri = "content://item?id=${id}&title=${title}"

val intent = Intent(Intent.ACTION_VIEW, Uri.parse(destUri))
startActivity(intent)

