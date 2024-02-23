/**
 * @file builtinfiles.h
 * @brief This file is part of the WebServer example for the ESP8266WebServer.
 *  
 * This file contains long, multiline text variables for  all builtin resources.
 */

// used for $upload.htm
static const char indexPage[] PROGMEM =
R"==(
<!doctype html>
<html lang='en'>

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>BarBot</title>
</head>

<body style="width:300px">
  <button id="mojito">mojito</button>
  <button id="tequila-sunrise">tequila sunrise</button>

  <script>

  const buttons = document.querySelectorAll('button');

  buttons.forEach((button) => {
    const id = button.id;
    button.addEventListener('click', () => makeCocktail(id));
  })

  function makeCocktail(id) {
    fetch(`/cocktails?id=${id}`, { method: 'POST'}).then(function () {
        window.alert('done.', id);
      });
  }

  </script>
</body>
)==";

// used for $upload.htm
static const char notFoundContent[] PROGMEM = R"==(
<html>
<head>
  <title>Ressource not found</title>
</head>
<body>
  <p>The ressource was not found.</p>
  <p><a href="/">Start again</a></p>
</body>
)==";
