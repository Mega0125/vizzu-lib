import { data } from '/test/integration/test_data/chart_types_eu.js';

const testSteps = [
    chart => chart.animate({
        data: Object.assign(data, {
            filter: record =>
            ['AT', 'BE', 'DE', 'DK', 'ES', 'FI', 'FR', 'IT', 'NL', 'SE']
            .includes(record.Country_code)
        }),
        config: {
            channels: {
                x: { set: ['Year', 'Joy factors'] },
                y: { set: ['Value 3 (+)', 'Country_code'] },
                color: { set: ['Country_code'] }
            },
            title: 'Stacked Streamgraph',
            geometry: 'area',
            align: 'center'
        }
    })
];

export default testSteps;