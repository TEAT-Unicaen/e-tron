import { useRef } from "react";
import { useNavigate } from "react-router-dom";
import { useFileData } from "../../store/json";

export function useFileSelector(getButton: boolean = true) {
    const fileInputRef = useRef<HTMLInputElement | null>(null);
    const { setFileData } = useFileData();
    const navigate = useNavigate();

    const handleButtonClick = () => {
        fileInputRef.current?.click();
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
                }
            };
            reader.readAsText(file);
        }
    };

    if (getButton) {
        return { fileInputRef, handleButtonClick, handleFileChange };
    }
    return { fileInputRef, handleFileChange };
}
