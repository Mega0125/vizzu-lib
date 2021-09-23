import { data } from '/test/integration/test_data/infinite_data.js';

const testSteps = [
    chart => chart.animate({
        data: data,
        config: {
            channels: {
                x: { set: ['Value 1', 'Joy factors'] },
                color: { set: ['Joy factors'] },
                label: { set: ['Value 1'] }
            },
            title: 'Pie Chart',
            coordSystem: 'polar'
        },
        style: { // All axes and axis labels are unnecessary on these types of charts. Meanwhile the marker labels are enlarged and their position is set. 
            plot: {
                marker: {       
                    label: {
                        fontSize: 13,
                        orientation: 'tangential',
                        angle: 4.7
                    }
                },
                xAxis: {  
                    title: { color: '#ffffff00' },
                    label: { color: '#ffffff00' },
                    ticks: { color: '#ffffff00' },
                    interlacing: { color: '#ffffff00' }
                },
                yAxis: {
                    color: '#ffffff00',
                    title: { color: '#ffffff00' },
                    label: { color: '#ffffff00' },
                    ticks: { color: '#ffffff00' }
                }
            }
        }
    }),
    chart => chart.animate({
        config: {
            channels: {
                x: { set: ['Value 1', 'Joy factors', 'Region', 'Country code'], },
                label: { set: null }
            }
        }
    }
    , '500ms'),
    chart => chart.animate({
        config: {
            channels: {
                x: { set: ['Value 1', 'Joy factors', 'Region', 'Country code'] },
                y: { 
                    set: ['Value 3'], 
                    range: { min: '-60%' } // Setting the radius of the empty circle in the centre.
                },
            },
            title: 'Coxcomb Chart'
        },
        style: {
            plot: {
                marker: {
                    borderWidth: 0,
			        borderOpacity: 1
                }
            }
        }
    })
];

export default testSteps;