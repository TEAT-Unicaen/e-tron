import styles from "./SideBar.module.scss";
import { useFileSelector } from "../common/selector/useFileSelector";

const SideBar: React.FC = ({}) => {
    
    const { fileInputRef, handleButtonClick ,handleFileChange } = useFileSelector(true);

    return (
        <>
            <div className={styles.sideBar}>
                <img src="/back.svg" onClick={() => {
                    window.location.href = "/";
                }}></img>
                <img src="/file.svg" onClick={
                    handleButtonClick
                }></img>
                <input
                    type="file"
                    accept="application/json"
                    ref={fileInputRef}
                    style={{display: "none"}}
                    onChange={handleFileChange}
                />
                <img src="/server.svg" onClick={() => alert("Cette fonctionnalitée n'est pas disponnible")}></img>
                <img src="/home.svg" onClick={() => {window.location.href = "/viewer"}}></img>
                <img src="/timeline.svg" onClick={() => {window.location.href = "/timeline"}}></img>
            </div>
        </>
    )
}

export default SideBar