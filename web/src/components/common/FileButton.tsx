import {useRef} from "react";
import { useNavigate } from "react-router-dom";

import Button from "./Button";
import {useFileData} from "../../store/json"

interface FileButtonProps {
    label: string;
}

export default function FileButton({label}: FileButtonProps) {
    const fileInput = useRef<HTMLInputElement | null>(null);
    const {setFileData} = useFileData();

    const navigate = useNavigate();

    const handleButtonClick = () => {
        fileInput.current?.click();
    };

    const handleFileChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        const file = event.target.files?.[0];
        if (file) {
            const reader = new FileReader();
            reader.onload = (e) => {
                const content = e.target?.result as string;
                try {
                    const json = JSON.parse(content);
                    setFileData(json);
                    console.log("Valid JSON:", json);
                    navigate("/viewer");
                } catch (error) {
                    alert("Seulement les fichiers JSON sont acceptés");
                    return;
                }
            };
            reader.readAsText(file);
        }
    };

    return (
        <>
            <Button label={label} onClick={handleButtonClick}/>
            <input
                type="file"
                accept="application/json"
                ref={fileInput}
                style={{display: "none"}}
                onChange={handleFileChange}
            />
        </>
    )
}