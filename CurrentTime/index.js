function showTime(){
    let time = new Date();
    let hour = time.getHours();
    let minute = time.getMinutes();
    let second = time.getSeconds();

    hour = hour < 10 ? '0' + hour : hour;
    minute = minute < 10 ? '0' + minute : minute;
    second = second < 10 ? '0' + second : second;

    document.getElementById('output').innerHTML = `${hour}:${minute}:${second}`;
}

setInterval(showTime, 1000);
window.onload = showTime;