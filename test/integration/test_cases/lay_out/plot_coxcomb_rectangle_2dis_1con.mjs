import { data } from '/test/integration/test_data/chart_types_eu.js';

const testSteps = [
    chart => chart.animate(
        {
            data: data,
            config:
            {
                channels:
                {
                    y: { attach: ['Joy factors', 'Value 2 (+)'], range: { min: '0%', max: '107.5%' } },
                    x: { attach: ['Year'] },
                    color: { attach: ['Joy factors'] }
                },
                title: null,
                coordSystem: 'polar',
                legend: null
            },
            style: 
            {
                plot: 
                { 
                    marker: 
                    {
                        borderOpacity:1
                    } 
                }
            }
        }
    )
];

export default testSteps;