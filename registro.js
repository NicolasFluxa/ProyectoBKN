var nombre = document.getElementById("nombreR");
let apellido = document.getElementById("apellidoR");
let correo = document.getElementById("correoR");
let password = document.getElementById("passwordR");
let confPassword = document.getElementById("confPasswordR");
let check = document.getElementById("checkR");
let form = document.getElementById("form");
let listInputs = document.querySelectorAll(".Registro");


form.addEventListener("submit", (e) => {
    e.preventDefault();
    let validacion = 0;
    if (nombre.value.trim() == "" ){
        validacion + 1;
        alert("Ingrese nombre");
    }
    if (apellido.value.trim() == "" ){
        alert("Ingrese Apellido");
        validacion + 1;
    }
    if (correo.value.trim() == "" ){
        alert("Ingrese correo");
        validacion + 1;
    }
    if (password.value.trim() == "" ){
        alert("Ingrese contraseña");
        validacion + 1;
    }
    if (password.value != confPassword.value) {
        alert("Confirmacion de contraseña erronea");
        validacion + 1;
    }
    if (!check.checked){
        alert("Acepte");
        validacion + 1;
    }

    

})


