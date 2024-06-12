document.addEventListener('DOMContentLoaded', (event) => {
    let upPressed = false;
    let downPressed = false;
    let leftPressed = false;
    let rightPressed = false;

    document.querySelectorAll('.control-button').forEach(button => {
        button.addEventListener('mousedown', (event) => {
            const key = event.target.getAttribute('data-key');
            handleKeyDown(key);
            button.setAttribute('data-interval', setInterval(() => handleKeyDown(key), 100));
        });

        button.addEventListener('mouseup', (event) => {
            clearInterval(event.target.getAttribute('data-interval'));
            handleKeyUp(event.target.getAttribute('data-key'));
        });

        button.addEventListener('mouseleave', (event) => {
            clearInterval(event.target.getAttribute('data-interval'));
            handleKeyUp(event.target.getAttribute('data-key'));
        });
    });

    document.addEventListener('keydown', (event) => {
        handleKeyDown(event.key);
    });

    document.addEventListener('keyup', (event) => {
        handleKeyUp(event.key);
    });

    function handleKeyDown(key) {
        switch(key) {
            case 'ArrowUp':
                upPressed = true;
                document.getElementById('up').classList.add('active');
                window.location.href = "/control?key=ArrowLeft";
                break;
            case 'ArrowDown':
                downPressed = true;
                document.getElementById('down').classList.add('active');
                window.location.href = "/control?key=ArrowRight";
                break;
            case 'ArrowLeft':
                leftPressed = true;
                document.getElementById('left').classList.add('active');
                window.location.href = "/control?key=ArrowUp";
                break;
            case 'ArrowRight':
                rightPressed = true;
                document.getElementById('right').classList.add('active');
                window.location.href = "/control?key=ArrowDown";
                break;
            case 'w':
                document.getElementById('w').classList.add('active');
                window.location.href = "/control?key=VerticalA";
                break;
            case 's':
                document.getElementById('s').classList.add('active');
                window.location.href = "/control?key=VerticalL";
                break;
            case 'a':
                document.getElementById('a').classList.add('active');
                window.location.href = "/control?key=HorizonL";
                break;
            case 'd':
                document.getElementById('d').classList.add('active');
                window.location.href = "/control?key=HorizonA";
                break;
        }
        updateStatus();
    }

    function handleKeyUp(key) {
        switch(key) {
            case 'ArrowUp':
                upPressed = false;
                document.getElementById('up').classList.remove('active');
                window.location.href = "/control?key=ArrowZero";
                break;
            case 'ArrowDown':
                downPressed = false;
                document.getElementById('down').classList.remove('active');
                window.location.href = "/control?key=ArrowZero";
                break;
            case 'ArrowLeft':
                leftPressed = false;
                document.getElementById('left').classList.remove('active');
                window.location.href = "/control?key=ArrowZero";
                break;
            case 'ArrowRight':
                rightPressed = false;
                document.getElementById('right').classList.remove('active');
                window.location.href = "/control?key=ArrowZero";
                break;
            case 'w':
                document.getElementById('w').classList.remove('active');
                window.location.href = "/control?key=KeyZero";
                break;
            case 's':
                document.getElementById('s').classList.remove('active');
                window.location.href = "/control?key=KeyZero";
                break;
            case 'a':
                document.getElementById('a').classList.remove('active');
                window.location.href = "/control?key=KeyZero";
                break;
            case 'd':
                document.getElementById('d').classList.remove('active');
                window.location.href = "/control?key=KeyZero";
                break;
        }
        updateStatus();
    }

    function updateStatus() {
        document.getElementById('status').innerText = `
            Up: ${upPressed},
            Down: ${downPressed},
            Left: ${leftPressed},
            Right: ${rightPressed}
        `;
    }
});
