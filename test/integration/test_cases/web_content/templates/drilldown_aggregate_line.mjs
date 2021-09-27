import { data } from '/test/integration/test_data/chart_types_eu.js';

const testSteps = [
    chart => chart.animate({
        data: data,
        config: {
            channels: {
                x: { set: ['Year'] },
                y: {
                    set: ['Value 3 (+)'],
                    /* Making the chart elements fill the whole of
                    the y-axis as the default value is now 110% */
                    range: {
                        max: '6000000000' 
                    }
                },
                /* Add the dimension that we’ll use 
                in the next state without splitting
                the lines in this state. */
                size: { set: ['Country'] } 
            },
            title: 'Line Chart',
            geometry: 'line'
        }
    }),
    chart => chart.animate({
        config: {
            channels: {
                color: { set: ['Country'] },
                /* We don’t need this dimension here anymore
                since it’s already on the 'color' channel. */
                size: { set: null }
            }
        }
    }),
    chart => chart.animate({
        config: {
            channels: {
                y: {
                    /* Setting back the y-axis range
                    to the default value. */
                    range: {
                        max: 'auto' 
                    }
                },
            }
        }
    })
];

export default testSteps;