const input = document.querySelector('.color-input');
const box = document.querySelector('.color-box');
input.addEventListener('input', function() {
    box.style.backgroundColor = input.value;
});
const box1 = document.querySelector('.color-box1');
const input1 = document.querySelector('.color-input1');
input1.addEventListener('input', function() {
    box1.style.backgroundColor = input1.value;
});
