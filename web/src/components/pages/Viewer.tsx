import BackgroundLayout from '../layout/BackgroundLayout'
import RadarChart from "../animated/chartjs/RadarChart";
import {useFileData} from "../../store/json"
import {processData} from "../../store/formatFileData"
import SideBar from '../layout/SideBar';

import AnimatedNumber from "../animated/simpleAnimated/framer"

import Table from "../common/table/table"

const Viewer: React.FC = () => {

    const formatedJSON = processData(useFileData().fileData)

    const size = formatedJSON.timeLog.length

    const columns = ["Player", "Murs"];

    return (
        <>  
            <div style={{display: 'flex', flexDirection: 'row', alignItems: 'center', justifyContent: 'center', gap: '10px'}}>
                <p>Nombre de tour :</p>
                <AnimatedNumber value={size} max={size}/>
            </div>
            <div style={{position: 'absolute', right: '15vh', top:'2.2vh'}}>
                <div style={{display: 'flex', flexDirection: 'row', alignItems: 'center', justifyContent: 'center', gap: '10px'}}>
                    <p>Temps de survie moyen : </p>
                    <AnimatedNumber value={formatedJSON.average} max={formatedJSON.average}/>
                </div>
            </div>

            <div style={{position: 'absolute', right: '15vh', overflowY: 'auto', height: '80vh', width: '20vh'}}>
                <Table data={formatedJSON.score} columns={columns}/>
            </div>

            <BackgroundLayout/>
            <SideBar/>
            <div style={{height: '90vh', width: '100vh' }}>
                <RadarChart data={formatedJSON.radar}/>
            </div>

        </>
    )
}

export default Viewer