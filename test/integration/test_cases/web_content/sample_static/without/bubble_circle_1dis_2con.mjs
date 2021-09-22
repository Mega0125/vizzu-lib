import { data } from '/test/integration/test_data/chart_types_eu.js';

const testSteps = [
    chart => chart.animate({
        data: data,
        config: {
            channels: {
                color: { set: ['Country_code'] },
                label: { set: ['Country_code'] },
                size: { set: ['Value 5 (+/-)'] }
            },
            title: 'Bubble Chart',
            geometry: 'circle'
        }
    })
];

export default testSteps;