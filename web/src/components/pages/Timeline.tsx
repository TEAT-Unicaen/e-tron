import React, {useState, useEffect} from 'react'
import BackgroundLayout from "../layout/BackgroundLayout"
import {useFileData} from "../../store/json"
import {processData} from "../../store/formatFileData"
import RangeSelector from '../common/selector/RangeSelector';
import LiveEventTimeline from '../layout/TimeLineLayout';
import SideBar from '../layout/SideBar';
import ToggleButton from '../common/buttons/Toggle';
const TimeLine: React.FC = () => {
    
    const formatedJSON = processData(useFileData().fileData)

    const [range, setRange] = useState<[number, number]>([0, formatedJSON.timeLog.length]);
    const handleChange = (range: [number, number]) => {
        setRange(range);
    }

    const [btn, setBtn] = useState<boolean>(false);
    const handleToggler = (val: boolean) => {
        setBtn(val);
    }

    const [draw, setDraw] = useState<boolean[]>(Array(formatedJSON.pNb+1).fill(true));

    const handlePlayer = (player: number) => (val: boolean) => {
        setDraw((prev) => {
            let newDraw = [...prev];
            newDraw[player] = val;
            return newDraw;
        });
    }

    const [events, setEvents] = useState<{ time: string; message: string }[]>([]);

    const [warning, setWarning] = useState<boolean>(false);

    useEffect(() => {   
        setEvents([]);
        if (range[1] - range[0] > 2048) {
            setWarning(true);
            range[1] = range[0] + 1024;
        }
        if (btn) {
            for (let i = range[0]; i < range[1]; i++) {
                const match = parseInt(formatedJSON.timeLog[i].match(/\d{1,2}$/));
                if (draw[match]) {
                    setEvents((prev) => [
                        { time: `Tour ${i}`, message: formatedJSON.timeLog[i] },
                        ...prev
                    ]);
                }
            }
        } else {
            for (let i = range[1] - 1; i >= range[0]; i--) {
                const match = parseInt(formatedJSON.timeLog[i].match(/\d{1,2}$/));
                if (draw[match]) {
                    setEvents((prev) => [
                        { time: `Tour ${i}`, message: formatedJSON.timeLog[i] },
                        ...prev
                    ]);
                }
            }
        }
    }, [range, btn, formatedJSON.timeLog, draw]);

    let playersButtons = [];

    for (let i = 0; i < formatedJSON.pNb; i++) {
        const lab = `Joueur ${i+1}`
        playersButtons.push(
            <ToggleButton key={i} label={lab} onChange={handlePlayer(i+1)} defaultValue={true} />
        )
    }

    return (
        <div style={{ display: 'flex', overflowY: 'scroll', maxHeight: '100vh', scrollbarWidth: 'none', msOverflowStyle: 'none'}}>
            <style>
            {`
            ::-webkit-scrollbar {
            display: none;
            }
            `}
            </style>
            {warning && (
                <div style={{ position: 'fixed', top: '10px', left: '50%', transform: 'translateX(-25%)', backgroundColor: 'red', color: 'white', padding: '10px', borderRadius: '5px', zIndex: 1000 }}>
                    La plage sélectionnée est trop grande. Elle a été réduite à 2048.
                </div>
            )}
            <div style={{ position: 'fixed', left: '25vh', top: '40vh', bottom: 0 }}>
            <RangeSelector min={0} max={formatedJSON.timeLog.length} onChange={handleChange}/>
            <ToggleButton label="Inverser l'ordre" onChange={handleToggler} />
            <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(100px, 1fr))', gap: '10px', maxWidth: '400px', marginTop: '20px', overflowY: 'auto', maxHeight: '40vh'}}>
                {playersButtons}
            </div>
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