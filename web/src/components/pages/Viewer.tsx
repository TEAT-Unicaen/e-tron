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

    const columns = ["Player", "Tour"];

    return (
        <>  
            <div style={{display: 'flex', flexDirection: 'row', alignItems: 'center', justifyContent: 'center', gap: '10px'}}>
                <p>Nombre de tour :</p>
                <AnimatedNumber value={size} max={size}/>
            </div>

            <div style={{position: 'absolute', right: '15vh'}}>
                <Table data={formatedJSON.score} columns={columns}/>
            </div>

            <BackgroundLayout/>
            <SideBar/>
            <div style={{height: '100vh', width: '100vh'}}>
                <RadarChart data={formatedJSON.radar}/>
            </div>

        </>
    )
}

export default Viewer