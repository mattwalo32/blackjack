var ws;

function cardCodeToString(code) {
    let suit = "";

    switch (suit % 4) {
        case 0:
            suit = "Diamonds";
            break;
        case 1:
            suit = "Hearts";
            break;
        case 2:
            suit = "Spades";
            break;
        case 3:
            suit = "Clubs";
    }

    let rankValue = Math.floor(code / 4) + 1;
    let rank = rankValue.toString();

    switch (rankValue) {
        case 1:
            rank = "Ace";
            break;
        case 11:
            rank = "Jack";
            break;
        case 12:
            rank = "Queen";
            break;
        case 13:
            rank = "King";
    }

    return rank.concat(" of ", suit);
}

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

        if (message.data.substring(0, 5) == "SEND:") {
            let cardCode = message.data.substring(5, 7);
            $("body").append("<p> You have " + cardCodeToString(cardCode) + "</p>");
        } else if (message.data.substring(0, 9) == "TIMELEFT:") {
            let time = message.data.substring(9, message.data.length);
            $("#timedialog").text("It's your turn! You have " + time + " seconds left.")

            if (time <= 0)
                $("#timedialog").text("It's not your turn yet.");

        }

       // $("body").append("<p>" + message.data + "</p>");
    };

    ws.onerror = function(error) {
        console.log('onerror ' + error);
        console.log(error);
    };

    $('#sendNameButton').click(function() {
    	ws.send("SETNAME:" + $('#name').val());
    });

    $('#hitButton').click(function () {
        ws.send("HIT:");
    });

    $('#standButton').click(function () {
        ws.send("STAND:");
    });

    /*$('#sendCommand').click(function() {
    	ws.send($('#command').val());
    });*/
});
