import React, {createContext, useContext, useState, useEffect} from "react";

const STORAGE_KEY = "fileData";

const FileDataContext =createContext<{
    fileData: any;
    setFileData: (data: any) => void;
} | null>(null);

export function FileDataProvider({children}: { children: React.ReactNode }) {
    const [fileData, setFileData] = useState<any>( () => {
        const data = localStorage.getItem(STORAGE_KEY);
        return data ? JSON.parse(data) : null;
    });

    useEffect(() => {
        if (fileData) {
            localStorage.setItem(STORAGE_KEY, JSON.stringify(fileData));
        }
    }, [fileData]);

    return (
        <FileDataContext.Provider value={{fileData, setFileData}}>
            {children}
        </FileDataContext.Provider>
    );
}

export function useFileData() {
    const context = useContext(FileDataContext);
    if (!context) {
        throw new Error("useFileData must be used within a FileDataProvider");
    }
    return context;
}