import Button from "./Button";
import { useFileSelector } from "./useFileSelector";

interface FileButtonProps {
    label: string;
}

export default function FileButton({label}: FileButtonProps) {

    const { fileInputRef, handleButtonClick, handleFileChange } = useFileSelector(true);

    return (
        <>
            <Button label={label} onClick={handleButtonClick}/>
            <input
                type="file"
                accept="application/json"
                ref={fileInputRef}
                style={{display: "none"}}
                onChange={handleFileChange}
            />
        </>
    )
}