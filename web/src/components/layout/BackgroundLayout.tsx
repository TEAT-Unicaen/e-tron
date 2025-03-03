import Glower from '../common/Glower'

const BackgroundLayout: React.FC = ({}) => {
    return (
        <>
            <Glower color='#4b38ec' width={120} height={100} top={-5} left={-20} opacity={0.05} rotation={33} blur={100}/>
            <Glower color='#bc07bc' width={110} height={100} top={40} left={120} opacity={0.05} rotation={60} blur={100}/>
        </>
    )
}

export default BackgroundLayout