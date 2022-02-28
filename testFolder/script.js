function backgroundRed() {
    document.body.style.backgroundColor = "red";
}

let button = document.getElementById("button");
button.addEventListener ('click', backgroundRed, true);
