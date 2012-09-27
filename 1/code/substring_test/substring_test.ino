String IRstring = "00000010010000000000"; 

if (IRstring.substring(8,11) == "000"){
  // Go Forward!
}
else if (IRstring.substring(8,11) == "010"){
  // Go Reverse!
}
else if (IRstring.substring(8,11) == "011"){
  // Go Left!
}
else if (IRstring.substring(8,11) == "100"){
  // Go Right!
}
