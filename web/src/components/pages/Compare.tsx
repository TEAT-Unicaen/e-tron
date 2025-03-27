import AnimatedNumber from '../animated/simpleAnimated/framer';
import BackgroundLayout from '../layout/BackgroundLayout'
import SideBar from '../layout/SideBar';
import Table from "../common/table/table"
import {useFileData} from "../../store/json"
import {processData} from "../../store/formatFileData"
import AreaChart, { AreaData } from "../animated/chartjs/aire"

const Home: React.FC = () => {

    const formatedJSON = processData(useFileData().fileData)
    const columns = ["Player", "Murs"];

    let allValues = Object.values(formatedJSON.aireTimeLine as Record<string, number>);
    let uniqueValues = Array.from(new Set(allValues));
    allValues.sort((a, b) => a - b);
    uniqueValues.sort((a, b) => a - b);
    const labels = uniqueValues.map(value => value.toString());

    let algoAndWall: any[] = [];
    allValues.forEach((value, index) => {
        if (algoAndWall[value]) {
            algoAndWall[value].val += formatedJSON.score[index].Murs
            algoAndWall[value].cpt += 1
        } else { 
            algoAndWall[value] = {
                val: formatedJSON.score[index].Murs,
                cpt: 1
            }
        }
    })

    let finalDat: number[] = [];
    algoAndWall.forEach((value) => {
        finalDat.push(value.val / value.cpt).toFixed(2)
    })

    
    const medianArray = Array(algoAndWall.length).fill(formatedJSON.timeLog.length / algoAndWall.length);

    const datas: AreaData = {
        labels: labels,
        datasets: [
            {
                label: "Temps de surive moyen selon la profondeur",
                data: finalDat,
                fill: true,
                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                borderColor: 'rgba(75, 192, 192, 1)',
                borderWidth: 1,
                tension: 0.4, 
            },
            {
                label: "Median",
                data: medianArray,
                fill: false,
                backgroundColor: 'rgba(255, 99, 132, 0.2)',
                borderColor: 'rgba(255, 99, 132, 1)',
                borderWidth: 1,
                tension: 1.0,
            }
        ]
    }

    return (
        <>
            <BackgroundLayout/>
            <SideBar/>

            <div style={{position: 'absolute', right: '15vh', top:'2.2vh'}}>
                <div style={{display: 'flex', flexDirection: 'row', alignItems: 'center', justifyContent: 'center', gap: '10px'}}>
                    <p>Temps de survie moyen : </p>
                    <AnimatedNumber value={formatedJSON.average} max={formatedJSON.average}/>
                </div>
            </div>

            <div style={{position: 'absolute', right: '15vh', overflowY: 'auto', height: '80vh', width: '20vh', top:'10.2vh'}}>
                <Table data={formatedJSON.score} columns={columns}/>
            </div>

            <div style={{height: '90vh', width: '100vh', position: 'fixed', left: '50vh', top: '20vh'}}>
                <p>{formatedJSON.algoType} ALGORITHM</p>
                <AreaChart data={datas}></AreaChart>
            </div>
        </>
    )
}

export default Home