function alertRmb() {
  // la variabile remember contiene un valore booleano (dipendente dallo stato della checkbox)
  var remember = document.getElementById("rmb").checked;
  if (remember) {
    alert("Hai scelto di essere ricordato");
  }
  else {
    alert("Hai scelto di non essere ricordato")
  }
  return remember;
}