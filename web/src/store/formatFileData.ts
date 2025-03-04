import {dataSet} from "../components/chartjs/RadarChart"

const backgroundColorSet = [
    'rgba(255, 0, 55, 0.2)',
    'rgba(0, 153, 255, 0.2)',
    'rgba(255, 183, 0, 0.2)',
    'rgba(255, 255, 255, 0.2)',
    'rgba(85, 0, 255, 0.2)',
    'rgba(21, 255, 0, 0.2)',
    'rgba(0, 0, 0, 0.2)',
    'rgba(95, 95, 95, 0.2)',
]

const secondColorSet = [
    'rgb(255, 0, 55)',
    'rgb(0, 153, 255)',
    'rgb(255, 183, 0)',
    'rgb(255, 255, 255)',
    'rgb(85, 0, 255)',
    'rgb(21, 255, 0)',
    'rgb(0, 0, 0)',
    'rgb(95, 95, 95)',
]

export function processData(inputArray: any[]): { radar: { labels: string[], datasets: dataSet[] }, [key: string]: any } {

    let outputArray: any[string] = {
        radar: {
            labels: [
                'Move up',
                'Move right',
                'Move down',
                'Move left',
            ],
            datasets : [] as dataSet[]
        }
    };

    let maxRound = 0
    let winner = null
    let index = 0

    for (const [pName, dat] of Object.entries(inputArray)) {
        let provRoundHere = dat.top + dat.bottom + dat.right + dat.left
        if (provRoundHere > maxRound) {
            maxRound = provRoundHere
            winner = pName
        }
        outputArray[pName] = {
            player: pName,
            roundPlayed: provRoundHere,
            top: dat.top,
            bottom: dat.bottom,
            right: dat.right,
            left: dat.left,
        }
        outputArray.radar.datasets.push({
            label: pName,
            data: [dat.top, dat.right, dat.bottom, dat.left],
            fill: true,
            backgroundColor: backgroundColorSet[index],
            borderColor: secondColorSet[index],
            pointBackgroundColor: secondColorSet[index],
            pointBorderColor: '#fff',
            pointHoverBackgroundColor: '#fff',
            pointHoverBorderColor: secondColorSet[index]
        })
        index++
    }

    return outputArray;
}