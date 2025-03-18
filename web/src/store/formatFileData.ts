import {dataSet} from "../components/animated/chartjs/RadarChart"

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
        },
        score: [],
        timeLog : {

        },
        average: 0.0,
    };

    let maxRound = 0
    let winner = null
    let index = 0
    let toalRound = 0

    for (const [pName, dat] of Object.entries(inputArray)) {
        if (pName === 'timeLog') {
            outputArray.timeLog = dat
        } else if (pName === 'numPlayers') {
            outputArray.pNb = dat
        } else {
            let provRoundHere = (dat.top ?? 0) + (dat.bottom ?? 0) + (dat.right ?? 0) + (dat.left ?? 0)
            toalRound += provRoundHere
            outputArray.score.push({
                Player: pName,
                Murs: provRoundHere
            })

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
                backgroundColor: backgroundColorSet[index%8],
                borderColor: secondColorSet[index%8],
                pointBackgroundColor: secondColorSet[index%8],
                pointBorderColor: '#fff',
                pointHoverBackgroundColor: '#fff',
                pointHoverBorderColor: secondColorSet[index%8]
            })
            index++
        }
    }

    outputArray.average = (toalRound / outputArray.pNb).toFixed(2)

    return outputArray;
}