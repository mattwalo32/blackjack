var ws;

$(function() {
    ws = new WebSocket('ws://' + document.location.host + '/socket');
    ws.onopen = function() {
        console.log('onopen');
        ws.send("SETTYPE:0"); // Type 0 is web client
    };

    ws.onclose = function() {
        $('#message').text('Lost connection.');
        console.log('onclose');
    };

    ws.onmessage = function(message) {
        console.log("got '" + message.data + "'");
        $("body").append("<p>" + message.data + "</p>");
    };

    ws.onerror = function(error) {
        console.log('onerror ' + error);
        console.log(error);
    };

    $('#sendNameButton').click(function() {
    	ws.send("SETNAME:" + $('#name').val());
    });

    $('#sendCommand').click(function() {
    	ws.send($('#command').val());
    });
});
