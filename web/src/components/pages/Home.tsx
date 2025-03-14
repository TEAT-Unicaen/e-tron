import Button from '../common/buttons/Button'
import FileButton from '../common/buttons/FileButton'
import BackgroundLayout from '../layout/BackgroundLayout'

const Home: React.FC = () => {
    return (
        <>
            <BackgroundLayout/>
            <div style={{display: 'flex', flexDirection: 'column', alignItems: 'center', justifyContent: 'center', gap: '20px'}}>
                <Button label="Charger les données du serveur" onClick={() => alert("Cette fonctionnalitée n'est pas disponnible")}/>
                <FileButton label='Charger des données locales' />
            </div>
        </>
    )
}

export default Home