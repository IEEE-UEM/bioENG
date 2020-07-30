const rows = [nome, idade, sexo];

let csvContent = "data: text/csv; charset = utf-8,";

rows.forEach(function(rowArray) {
    let row = rowArray.join(",");
    csvContent += row + "\r\n";
})

var encodedUri = encondeURI(csvContent);
window.open(encodedUri);