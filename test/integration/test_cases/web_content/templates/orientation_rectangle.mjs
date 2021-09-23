import { data } from '/test/integration/test_data/tutorial.js';

const testSteps = [
  chart => chart.animate({
    data: data,
    config: {
      channels: {
        x: { set: ['Timeseries'] },
        y: { set: ['Values 1', 'Categ. Parent'] },
        color: { set: ['Categ. Parent'] },
        label: { set: ['Values 1'] }
      },
      title: 'Stacked Column Chart'
    }
  }),
  chart => chart.animate({
    config: {
      channels: {
        x: { set: ['Values 1', 'Timeseries'] },
        y: { set: ['Categ. Parent'] },
      },
      legend: null,
      title: 'Stacked Bar Chart',
    }
  }),
  chart => chart.animate({
    config: {
      channels: {
        x: { set: ['Values 1'] }, // Taking the dimension off to show the sum of the newly stacked elements.
      }
    }
  })
];

export default testSteps;