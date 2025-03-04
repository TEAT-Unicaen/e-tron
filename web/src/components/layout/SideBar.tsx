import styles from "./SideBar.module.scss";

const SideBar: React.FC = ({}) => {
    
    return (
        <>
            <div className={styles.sideBar}>
                <img src="/back.svg" onClick={() => {
                    window.location.href = "/";
                }}></img>
            </div>
        </>
    )
}

export default SideBar