$(function () {
  document.queryCommandSupported("copy") &&
    ($("figure").before(
      '<div class="div-sample-copy"><span class="btn-sample-copy">Copy</span></div>'
    ),
    $(".btn-sample-copy").click(function () {
      window.getSelection().removeAllRanges();
      try {
        var e = document.createRange();
        e.selectNode($(this).parent().next("figure").get()[0]),
          window.getSelection().addRange(e),
          document.execCommand("copy");
      } catch (o) {
        console.log(o);
      }
      window.getSelection().removeAllRanges();
    }));
});
