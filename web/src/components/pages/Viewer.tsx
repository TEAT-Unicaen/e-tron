import BackgroundLayout from '../layout/BackgroundLayout'
import RadarChart from "../chartjs/RadarChart";
import {useFileData} from "../../store/json"
import {processData} from "../../store/formatFileData"
import SideBar from '../layout/SideBar';


const Viewer: React.FC = () => {

    const formatedJSON = processData(useFileData().fileData)

    return (
        <>
            <BackgroundLayout/>
            <SideBar/>
            <div style={{height: '100vh', width: '100vh'}}>
                <RadarChart data={formatedJSON.radar}/>
            </div>

        </>
    )
}

export default Viewer