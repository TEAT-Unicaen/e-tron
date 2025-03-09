import React, {useState, useEffect} from 'react'
import BackgroundLayout from "../layout/BackgroundLayout"
import {useFileData} from "../../store/json"
import {processData} from "../../store/formatFileData"
import RangeSelector from '../common/RangeSelector';
import LiveEventTimeline from '../layout/TimeLineLayout';
import SideBar from '../layout/SideBar';
import ToggleButton from '../common/Toggle';

const TimeLine: React.FC = () => {
    
    const formatedJSON = processData(useFileData().fileData)

    const [range, setRange] = useState<[number, number]>([0, formatedJSON.timeLog.length]);
    const handleChange = (range: [number, number]) => {
        setRange(range);
    }

    const [btn, setBtn] = useState<boolean>(true);
    const handleToggler = (val: boolean) => {
        setBtn(val);
    }

    const [events, setEvents] = useState<{ time: string; message: string }[]>([]);

    useEffect(() => {   
        setEvents([]);
        if (btn) {
            for (let i = range[0]; i < range[1]; i++) {
                setEvents((prev) => [
                    { time: `Tour ${i}`, message: formatedJSON.timeLog[i] },
                    ...prev
                ]);
            }
        } else {
            for (let i = range[1] - 1; i >= range[0]; i--) {
                setEvents((prev) => [
                    { time: `Tour ${i}`, message: formatedJSON.timeLog[i] },
                    ...prev
                ]);
            }
        }
    }, [range, btn, formatedJSON.timeLog]);

    return (
        <div style={{ display: 'flex', overflowY: 'scroll', maxHeight: '100vh', scrollbarWidth: 'none', msOverflowStyle: 'none'}}>
            <style>
            {`
            ::-webkit-scrollbar {
            display: none;
            }
            `}
            </style>
            <div style={{ position: 'fixed', left: '25vh', top: '40vh', bottom: 0 }}>
            <RangeSelector min={0} max={formatedJSON.timeLog.length} onChange={handleChange}/>
            <ToggleButton label="Inverser l'ordre" onChange={handleToggler} />
            </div>
            <div style={{ marginLeft: '200px', width: '100%' }}>
            <BackgroundLayout/>
            <SideBar/>
            <LiveEventTimeline events={events}/>
            </div>
        </div>
    )
}

export default TimeLine