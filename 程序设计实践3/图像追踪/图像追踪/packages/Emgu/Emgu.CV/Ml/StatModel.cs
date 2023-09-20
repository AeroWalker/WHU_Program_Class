//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using Emgu.CV.ML.MlEnum;
using Emgu.Util;

namespace Emgu.CV.ML
{
    /// <summary>
    /// Interface for statistical models in OpenCV ML.
    /// </summary>
    public interface IStatModel : IAlgorithm
    {
        /// <summary>
        /// Return the pointer to the StatModel object
        /// </summary>
        /// <returns>The pointer to the StatModel object</returns>
        IntPtr StatModelPtr { get; }
    }

    /// <summary>
    /// A statistic model
    /// </summary>
    public static class StatModelExtensions
    {
        /// <summary>
        /// Trains the statistical model.
        /// </summary>
        /// <param name="model">The stat model.</param>
        /// <param name="samples">The training samples.</param>
        /// <param name="layoutType">Type of the layout.</param>
        /// <param name="responses">Vector of responses associated with the training samples.</param>
        /// <returns>True if the training is successful.</returns>
        public static bool Train(this IStatModel model, IInputArray samples, DataLayoutType layoutType, IInputArray responses)
        {
            using (InputArray iaSamples = samples.GetInputArray())
            using (InputArray iaResponses = responses.GetInputArray())
            {
                return MlInvoke.StatModelTrain(model.StatModelPtr, iaSamples, layoutType, iaResponses);
            }
        }

        /// <summary>
        /// Trains the statistical model.
        /// </summary>
        /// <param name="model">The model.</param>
        /// <param name="trainData">The train data.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>True if the training is successful.</returns>
        public static bool Train(this IStatModel model, TrainData trainData, int flags = 0)
        {
            return MlInvoke.StatModelTrainWithData(model.StatModelPtr, trainData, flags);
        }

        /// <summary>
        /// Predicts response(s) for the provided sample(s)
        /// </summary>
        /// <param name="model">The model.</param>
        /// <param name="samples">The input samples, floating-point matrix.</param>
        /// <param name="results">The optional output matrix of results.</param>
        /// <param name="flags">The optional flags, model-dependent.</param>
        /// <returns>Response for the provided sample</returns>
        public static float Predict(this IStatModel model, IInputArray samples, IOutputArray results = null, int flags = 0)
        {
            using (InputArray iaSamples = samples.GetInputArray())
            using (OutputArray oaResults = results == null ? OutputArray.GetEmpty() : results.GetOutputArray())
            {
                return MlInvoke.StatModelPredict(model.StatModelPtr, iaSamples, oaResults, flags);
            }
        }

    }
}
