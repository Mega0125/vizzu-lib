import { data } from '/test/integration/test_data/chart_types_eu.js';

const testSteps = [
    chart => chart.animate(
        {
            data: data,
            config:
            {
                channels:
                {
                    y: { attach: ['Joy factors'] },
                    x: { attach: ['Value 2 (+)'], range: { min: '0%', max: '133%' } },
                    color: { attach: ['Joy factors'] }
                },
                title: 'Radial Chart',
                coordSystem: 'polar'
            },
            style:
            {
                plot:
                { 
                  yAxis:
                    { 
                        label:
                        { 
                            paddingRight: 20
                        }
                    
                    }
                }
            }
        }
    )
];

export default testSteps;