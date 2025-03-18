

type TableProps = {
    data: any[];
    columns: string[];
    sort?: boolean;
}

const Table: React.FC<TableProps> = ({ data, columns, sort=true }) => {

    if (sort) {
        data.sort((a, b) => b[columns[1]] - a[columns[1]]);
    }

    return (
        <>
            <table>
                <thead>
                    <tr>
                        {columns.map((column, index) => (
                            <th key={index}>{column}</th>
                        ))}
                    </tr>
                </thead>
                <tbody>
                    {data.map((row, index) => (
                        <tr key={index}>
                            {columns.map((column, index) => (
                                <td key={index}>{row[column]}</td>
                            ))}
                        </tr>
                    ))}
                </tbody>
            </table>
        </>
    );
};

export default Table;