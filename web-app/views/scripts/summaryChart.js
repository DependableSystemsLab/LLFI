
var randomScalingFactor = function() {
    return 1;
};

var horizontalBarChartData = {
    labels: ["SDC", "Hanged", "Crashed"],
    datasets: [{
        label: 'Dataset 1',
        backgroundColor: "rgba(220,220,220,0.5)",
        data: [randomScalingFactor(), randomScalingFactor(), randomScalingFactor()]
    }]

};

window.onload = function() {
    var ctx = document.getElementById("faultSummary").getContext("2d");
    window.myHorizontalBar = new Chart(ctx, {
        type: 'horizontalBar',
        data: horizontalBarChartData,
        options: {
            // Elements options apply to all of the options unless overridden in a dataset
            // In this case, we are setting the border of each horizontal bar to be 2px wide and green
            elements: {
                rectangle: {
                    borderWidth: 1,
                    borderColor: 'rgb(0, 255, 0)',
                    borderSkipped: 'left'
                }
            },
            responsive: true,
            legend: {
                position: 'right',
            },
            title: {
                display: true,
                text: 'Fault Summary'
            }
        }
    });

};