import { data } from '/test/integration/test_data/chart_types_eu.js';

data.filter = record => 
record.Country == 'Belgium';

const testSteps = [
    chart => chart.animate(
        {
            data: data,
            config:
            {
                channels:
                {
                    y: { attach: ['Year', 'Value 5 (+/-)'], range: '0,1.1,%' },
                    x: { attach: ['Year'] },
                    color: { attach: ['Country'] },
                    label: { attach: ['Value 5 (+/-)'] },
                    lightness: { attach: ['Year'] }
                },
                title: 'Waterfall Chart with (-) Nums (Belgium)',
                legend: null
            },
            style:
            {
                plot: {
                    marker: {
                        label: {
                            position: 'top'
                        }
                    }
                }
            }
        }
    )
];

export default testSteps;